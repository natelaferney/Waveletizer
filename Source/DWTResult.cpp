#include "DWTResult.h"
#include <vector>
#include <string>
#include "WaveletFilters3.h"


DWTResult::DWTResult() :
	currentLevel(0), filterName("D1"), reserveBufferSize(0)
{
	//filtcoef(filterName, flp, fhp, rlp, rhp);
	//createWaveletFilterMap(waveletFilters);
	updateFilter("D1");
}

DWTResult::DWTResult(std::string filter) :
	currentLevel(0), filterName(filter), reserveBufferSize(0)
{
	//filtcoef(filterName, flp, fhp, rlp, rhp);
	//createWaveletFilterMap(waveletFilters);
	updateFilter(filter);
};

DWTResult::~DWTResult() {};

void DWTResult::updateFilter(std::string filter)
{
	flp.clear();
	fhp.clear();
	rlp.clear();
	rhp.clear();
	filterName = filter;
	filtcoef(filterName, flp, fhp, rlp, rhp);
};

std::string DWTResult::getCurrentFilter()
{
	return filterName;
}

int DWTResult::sign(int X)
{
	bool greaterThan = (X >= 0);
	int ret;
	switch (greaterThan)
	{
	case true:
		ret = 1;
		break;
	case false:
		ret = -1;
		break;
	}
	return ret;
};

void DWTResult::circshift(std::vector<float> &sig_cir, int S, int L, int N)
{
	const int sigSize = N;
	L = ((abs(L) > sigSize) ? (sign(L) * (abs(L) % sigSize)) : L);
	L = ((L < 0) ? ((sigSize + L) % sigSize) : L);
	rotate(sig_cir.begin()+S, sig_cir.begin() + L + S, sig_cir.begin() + sigSize + S);
};

void DWTResult::filterAndDownSample(const float * input, const std::vector<float> &filter, std::vector<float> &output, const int nf)
{
	fill(output.begin(), output.end(), 0);
	int const ng = filter.size();
	int const n = nf + ng - 1;
	int const h = nf / 2;
	for (auto i(0); i < n; i += 2) {
		int jmn = (i >= ng - 1) ? i - (ng - 1) : 0;
		int jmx = (i <  nf - 1) ? i : nf - 1;
		float temp = 0.0;
		for (auto j(jmn); j <= jmx; ++j) {
			temp += (input[j] * filter[i - j]);
		}
		output[(i / 2) % h] += temp;
	}
};

void DWTResult::filterAndUpSample(const float * input, const std::vector<float> &filter, std::vector<float> &output, const int nf)
{
	fill(output.begin(), output.end(), 0);
	int const ng = filter.size();
	int const n = nf + ng - 1;
	for (auto i(0); i < n; ++i)
	{
		int jmn = (i >= ng - 1) ? i - (ng - 1) : 0;
		int jmx = (i <  nf - 1) ? i : nf - 1;
		float temp = 0.0;
		for (auto j(jmn); j <= jmx; ++j)
		{
			float dog = ((j % 2) == 0) ? (input[j / 2] * filter[i - j]) : 0.0;
			temp += dog;
		}
		output[i % nf] += temp;
	}
}

void DWTResult::reserveBuffer(int size)
{
	//result.resize(size);
	result.reserve(size);
	int newSize = size + 100;
	bufferLP.reserve(newSize);
	bufferHP.reserve(newSize);
	reserveBufferSize = size;
};

int DWTResult::getReserveBufferSize()
{
	return reserveBufferSize;
}

void DWTResult::dwt(int level)
{
	const unsigned int inputSignalSize = result.size();
	const unsigned int filterSize = flp.size();
	const unsigned int convSize = inputSignalSize + filterSize - 1;
	const unsigned int Lh = filterSize / 2;
	const unsigned int N = inputSignalSize / 2;
	int d;
	int n;

	for (int i = 1; i <= level; ++i)
	{
		d = (int)((inputSignalSize / std::pow(2, i)) + 0.5f);
		n = 2 * d;
	
		circshift(result, 0, -Lh, n);
		
		//low pass portion
		bufferLP.resize(d, 0.0f);
		filterAndDownSample(&result[0], flp, bufferLP, n);

		//high pass portion
		bufferHP.resize(d, 0.0f);
		filterAndDownSample(&result[0], fhp, bufferHP, n);

		//put the data back in result
		circshift(bufferLP, 0, Lh, d);
		circshift(bufferHP, 0, Lh, d);
		copy(bufferLP.begin(), bufferLP.end(), result.begin());
		copy(bufferHP.begin(), bufferHP.end(), result.begin() + d);
		++currentLevel;
	}
};

void DWTResult::idwt(int level)
{
	const unsigned int inputSignalSize = result.size();
	const unsigned int filterSize = rlp.size();
	const unsigned int Lh = filterSize / 2;
	int d;
	int n;

	for (int i = level; i > 0; --i)
	{
		d = (int)((inputSignalSize / std::pow(2, i)) + 0.5f);
		n = 2 * d;
		//std::cout << d << '\n';
		circshift(result, 0, -Lh, d);
		circshift(result, d, -Lh, d);
		
		//low pass portion
		bufferLP.resize(n, 0.0f);
		filterAndUpSample(&result[0], rlp, bufferLP, n);

		//high pass portion
		bufferHP.resize(n, 0.0f);
		filterAndUpSample(&result[d], rhp, bufferHP, n);

		for (int i = 0; i < n; ++i) 
		{
			result[i] = bufferLP[i] + bufferHP[i];
		}
		circshift(result, 0, filterSize + Lh - 1, n);
		--currentLevel;
	}


}

void DWTResult::applyGain(float gainLP, float gainHP, int level)
{
	const unsigned int inputSignalSize = result.size();
	int d = (int)((inputSignalSize / std::pow(2, level)) + 0.5f);
	for (int i = 0; i < d; ++i) result[i] *= gainLP;
	for (int i = d; i < inputSignalSize; ++i) result[i] *= gainHP;
}

void DWTResult::applyGain2(float gainLP, float gainHP, int level)
{
	const unsigned int inputSignalSize = result.size();
	const int d = (int)((inputSignalSize / std::pow(2, level)) + 0.5f);
	for (int i = 0; i < d; ++i) result[i] *= gainLP;
	for (int i = d; i < 2*d; ++i) result[i] *= gainHP;
}

inline float DWTResult::upsampleBy2(const float * f, const int index)
{
	bool isEven = ((index % 2) == 0);

	switch (isEven)
	{
	case true:
		return f[(index / 2)];
		break;
	case false:
		return 0.0f;
		break;
	}
}