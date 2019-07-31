#ifndef DWTRESULT_H
#define DWTRESULT_H
#include <vector>
#include <string>
#include <map>

class DWTResult {
public:
	//constructors and destructors
	DWTResult();
	DWTResult(std::string filter);
	~DWTResult();

	//public members
	std::vector<float> result;

	//public functions
	void dwt(int level);
	void idwt(int level);
	void updateFilter(std::string filter);
	void applyGain(float gainLP, float gainHP, int level);
	void applyGain2(float gainLP, float gainHP, int level);
	void reserveBuffer(int size);
	int getReserveBufferSize();
	std::string getCurrentFilter();

private:
	//private members
	int currentLevel;
	int reserveBufferSize;
	std::string filterName;
	std::vector<float> flp;
	std::vector<float> fhp;
	std::vector<float> rlp;
	std::vector<float> rhp;
	std::vector<float> bufferLP;
	std::vector<float> bufferHP;

	//private functions
	void filterAndDownSample(const float * input, const std::vector<float> &filter, std::vector<float> &output, const int nf);
	void filterAndUpSample(const float * input, const std::vector<float> &filter, std::vector<float> &output, const int nf);
	void circshift(std::vector<float> &sig_cir, int S, int L, int N);
	inline float upsampleBy2(const float * f, const int index);
	int sign(int);
};

#endif