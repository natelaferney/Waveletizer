#pragma once
//This file was machine generated
#include <vector>
void filtcoef(std::string filterChoice, std::vector<float> &flp, std::vector<float> &fhp, std::vector<float> &rlp, std::vector<float> &rhp)
{
	//haar
	if ("Haard" == filterChoice)
	{
		float flp_temp[] = { 0.7071067811865476f,0.7071067811865476f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { -0.7071067811865476f,0.7071067811865476f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { 0.7071067811865476f,0.7071067811865476f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { 0.7071067811865476f,-0.7071067811865476f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	// db2
	else if ("Doe Bah Shee 4" == filterChoice)
	{
		float flp_temp[] = { -0.12940952255126037f,0.2241438680420134f,0.8365163037378079f,0.48296291314453416f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { -0.48296291314453416f,0.8365163037378079f,-0.2241438680420134f,-0.12940952255126037f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { 0.48296291314453416f,0.8365163037378079f,0.2241438680420134f,-0.12940952255126037f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { -0.12940952255126037f,-0.2241438680420134f,0.8365163037378079f,-0.48296291314453416f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	// db3
	else if ("Doe Bah Shee 6" == filterChoice)
	{
		float flp_temp[] = { 0.03522629188570953f,-0.08544127388202666f,-0.13501102001025458f,0.45987750211849154f,0.8068915093110925f,0.33267055295008263f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { -0.33267055295008263f,0.8068915093110925f,-0.45987750211849154f,-0.13501102001025458f,0.08544127388202666f,0.03522629188570953f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { 0.33267055295008263f,0.8068915093110925f,0.45987750211849154f,-0.13501102001025458f,-0.08544127388202666f,0.03522629188570953f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { 0.03522629188570953f,0.08544127388202666f,-0.13501102001025458f,-0.45987750211849154f,0.8068915093110925f,-0.33267055295008263f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	// coif1
	else if ("Coif" == filterChoice)
	{
		float flp_temp[] = { -0.015655728135791993f,-0.07273261951252645f,0.3848648468648578f,0.8525720202116004f,0.3378976624574818f,-0.07273261951252645f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { 0.07273261951252645f,0.3378976624574818f,-0.8525720202116004f,0.3848648468648578f,0.07273261951252645f,-0.015655728135791993f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { -0.07273261951252645f,0.3378976624574818f,0.8525720202116004f,0.3848648468648578f,-0.07273261951252645f,-0.015655728135791993f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { -0.015655728135791993f,0.07273261951252645f,0.3848648468648578f,-0.8525720202116004f,0.3378976624574818f,0.07273261951252645f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	// Bior 1.3
	else if ("Bior1" == filterChoice)
	{
		float flp_temp[] = { -0.08838834764831845f,0.08838834764831845f,0.7071067811865476f,0.7071067811865476f,0.08838834764831845f,-0.08838834764831845f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { -0.0f,0.0f,-0.7071067811865476f,0.7071067811865476f,-0.0f,0.0f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { 0.0f,0.0f,0.7071067811865476f,0.7071067811865476f,0.0f,0.0f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { -0.08838834764831845f,-0.08838834764831845f,0.7071067811865476f,-0.7071067811865476f,0.08838834764831845f,0.08838834764831845f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	//Bior 2.2
	else if ("Bior2" == filterChoice)
	{
		float flp_temp[] = { 0.0f,-0.1767766952966369f,0.3535533905932738f,1.0606601717798212f,0.3535533905932738f,-0.1767766952966369f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { -0.0f,0.3535533905932738f,-0.7071067811865476f,0.3535533905932738f,-0.0f,0.0f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { 0.0f,0.3535533905932738f,0.7071067811865476f,0.3535533905932738f,0.0f,0.0f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { 0.0f,0.1767766952966369f,0.3535533905932738f,-1.0606601717798212f,0.3535533905932738f,0.1767766952966369f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	//Bior 3.1
	else if ("Nail Bat" == filterChoice)
	{
		float flp_temp[] = { -0.3535533905932738f,1.0606601717798212f,1.0606601717798212f,-0.3535533905932738f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { -0.1767766952966369f,0.5303300858899106f,-0.5303300858899106f,0.1767766952966369f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { 0.1767766952966369f,0.5303300858899106f,0.5303300858899106f,0.1767766952966369f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { -0.3535533905932738f,-1.0606601717798212f,1.0606601717798212f,0.3535533905932738f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	//Bior 3.3
	else if ("Bior3" == filterChoice)
	{
		float flp_temp[] = { 0.06629126073623882f,-0.1988737822087165f,-0.15467960838455727f,0.9943689110435825f,0.9943689110435825f,-0.15467960838455727f,-0.1988737822087165f,0.06629126073623882f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { -0.0f,0.0f,-0.1767766952966369f,0.5303300858899106f,-0.5303300858899106f,0.1767766952966369f,-0.0f,0.0f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { 0.0f,0.0f,0.1767766952966369f,0.5303300858899106f,0.5303300858899106f,0.1767766952966369f,0.0f,0.0f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { 0.06629126073623882f,0.1988737822087165f,-0.15467960838455727f,-0.9943689110435825f,0.9943689110435825f,0.15467960838455727f,-0.1988737822087165f,-0.06629126073623882f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	//sym3
	else if ("Sym" == filterChoice)
	{
		float flp_temp[] = { 0.035226291882100656f, -0.08544127388224149f, -0.13501102001039084f, 0.4598775021193313f, 0.8068915093133388f, 0.3326705529509569f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { -0.3326705529509569f, 0.8068915093133388f, -0.4598775021193313f, -0.13501102001039084f, 0.08544127388224149f, 0.035226291882100656f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { 0.3326705529509569f, 0.8068915093133388f, 0.4598775021193313f, -0.13501102001039084f, -0.08544127388224149f, 0.035226291882100656f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { 0.035226291882100656f, 0.08544127388224149f, -0.13501102001039084f, -0.4598775021193313f, 0.8068915093133388f, -0.3326705529509569f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	//rbio1.3
	else if ("Gaussian" == filterChoice)
	{
		float flp_temp[] = { 0.1767766952966369f, 0.5303300858899106f, 0.5303300858899106f, 0.1767766952966369f };
		flp.assign(flp_temp, flp_temp + sizeof(flp_temp) / sizeof(float));
		float fhp_temp[] = { 0.3535533905932738f, 1.0606601717798212f, -1.0606601717798212f, -0.3535533905932738f };
		fhp.assign(fhp_temp, fhp_temp + sizeof(fhp_temp) / sizeof(float));
		float rlp_temp[] = { -0.3535533905932738f, 1.0606601717798212f, 1.0606601717798212f, -0.3535533905932738f };
		rlp.assign(rlp_temp, rlp_temp + sizeof(rlp_temp) / sizeof(float));
		float rhp_temp[] = { 0.1767766952966369f, -0.5303300858899106f, 0.5303300858899106f, -0.1767766952966369f };
		rhp.assign(rhp_temp, rhp_temp + sizeof(rhp_temp) / sizeof(float));
	}
	else {}
}