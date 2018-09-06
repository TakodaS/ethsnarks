#include "longsightl_constants.hpp"

using ethsnarks::FieldT;


void LongsightL12p5_constants_fill( std::vector<FieldT> &round_constants )
{
	round_constants.resize(12);
	round_constants[0] = FieldT("0");
	round_constants[1] = FieldT("1123290141928164279008888891766378473818224497744673926276953901234820430642");
	round_constants[2] = FieldT("10985366949788476814992264851760069583580863264413713065688271499338204201663");
	round_constants[3] = FieldT("697060791212164642694445403044920191448639837622426114750683064775524708091");
	round_constants[4] = FieldT("2927275006259720461621994090854281014055545305739622272831795049357503845045");
	round_constants[5] = FieldT("10412319102912193718627660805338892121530111706856302539498702298083887810988");
	round_constants[6] = FieldT("620349011339579072558087154478991228793293385614105914560448303472115289790");
	round_constants[7] = FieldT("10511143232444605554382744833253216315052468071414858166502934581708567653712");
	round_constants[8] = FieldT("14812403264587974755203859916430999098674340519454779971315944472173228373660");
	round_constants[9] = FieldT("11084405208266551212633630110871834096841516447067573520449405021724864800341");
	round_constants[10] = FieldT("5309209836577867454067352188316145237209274990329546025817814580523329585168");
	round_constants[11] = FieldT("0");
}


const std::vector<FieldT> LongsightL12p5_constants_assign( )
{
    std::vector<FieldT> round_constants;

    LongsightL12p5_constants_fill(round_constants);

    return round_constants;
}
