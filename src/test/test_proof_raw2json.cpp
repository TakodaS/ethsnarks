#include "export.cpp"
#include "import.cpp"
#include "utils.cpp"


using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::stringstream;


int main( int argc, char **argv )
{
	typedef libff::alt_bn128_pp ppT;
	ppT::init_public_params();

	if( argc < 3 ) {
		cerr << "Usage: " << argv[0] << " <input-proof.json> <check-proof.raw>" << endl;
		return 1;
	}

	ifstream original_proof_input(argv[1]);
	stringstream original_proof_stream;
	original_proof_stream << original_proof_input.rdbuf();
	auto original_proof_json = proof_from_json<ppT>(original_proof_stream);

	// Load raw serialised proof
	auto proof = loadFromFile<r1cs_gg_ppzksnark_zok_proof<ppT>> (argv[2]);

	// Dump JSON serialised proof
	auto proof_json_serialised = proof_to_json<ppT>(proof, original_proof_json.first);

	// Load JSON serialised proof
	stringstream proof_stream;
	proof_stream << proof_json_serialised;
	auto proof_json = proof_from_json<ppT>(proof_stream);

	// Verify serialisation is correct
	if( ! (proof_json.second == proof) ) {
		cerr << "FAIL\n";
		return 1;
	}

	cout << "OK";
	return 0;
}