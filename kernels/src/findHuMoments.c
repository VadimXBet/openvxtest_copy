#include "detail/types.h"
#include "detail/momentsStruct.h"

void findHuMoments(const momentsStruct moments, vx_array humoments)
{
	vx_float64* H = humoments->data;

	double nu20_m_nu02 = moments->nu20 - moments->nu02;
	double nu30_m_3nu12 = moments->nu30 - 3 * moments->nu12;
	double nu213_m_nu03 = 3 * moments->nu21 - moments->nu03;
	double nu30_p_nu12 = moments->nu30 + moments->nu12;
	double nu21_p_nu03 = moments->nu21 + moments->nu03;

	H[0] = moments->nu20 + moments->nu02;
	H[1] = nu20_m_nu02 * nu20_m_nu02 + 4 * moments->nu11 * moments->nu11;
	H[2] = nu30_m_3nu12 * nu30_m_3nu12 + nu213_m_nu03 * nu213_m_nu03;
	H[3] = nu30_p_nu12 * nu30_p_nu12 + nu21_p_nu03 * nu21_p_nu03;
	H[4] = nu30_m_3nu12 * nu30_p_nu12 * (nu30_p_nu12 * nu30_p_nu12 - 3 *
		nu21_p_nu03 * nu21_p_nu03) + nu213_m_nu03 * nu21_p_nu03 *
		(3 * nu30_p_nu12 * nu30_p_nu12 - nu21_p_nu03 * nu21_p_nu03);
	H[5] = nu20_m_nu02 * (nu30_p_nu12 * nu30_p_nu12 - nu21_p_nu03 * nu21_p_nu03)
		+ 4 * moments->nu11 * nu30_p_nu12 * nu21_p_nu03;
	H[6] = nu213_m_nu03 * nu30_p_nu12 * (nu30_p_nu12 * nu30_p_nu12 -
		3 * nu21_p_nu03 * nu21_p_nu03) - nu30_m_3nu12 * nu21_p_nu03 *
		(3 * nu30_p_nu12 * nu30_p_nu12 - nu21_p_nu03 * nu21_p_nu03);
}