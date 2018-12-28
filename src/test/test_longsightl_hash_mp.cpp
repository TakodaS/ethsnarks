// Copyright (c) 2018 HarryR
// License: LGPL-3.0+


#include "gadgets/longsightl.hpp"
#include "stubs.hpp"

namespace ethsnarks {

const FieldT run_LongsightL(int n_msgs, const char **msgs)
{
    std::vector<FieldT> round_constants;
    LongsightL12p5_constants_fill(round_constants);

    ProtoboardT pb;

    std::vector<VariableT> v_msgs;
    for( int i = 0; i < n_msgs; i++ )
    {
        v_msgs.emplace_back(make_variable(pb, FieldT(msgs[i]), FMT("msgs","[%u]", i)));
    }
    pb.set_input_sizes(n_msgs);

    // Private inputs
    VariableT iv = make_variable(pb, FieldT("918403109389145570117360101535982733651217667914747213867238065296420114726"), "iv");

    LongsightL12p5_MP_gadget the_gadget(pb, iv, v_msgs, "gadget");
    the_gadget.generate_r1cs_witness();

    return pb.val(the_gadget.result());
}

bool test_LongsightL()
{
    std::vector<FieldT> round_constants;
    LongsightL12p5_constants_fill(round_constants);

    ProtoboardT pb;

    // Public inputs
    VariableT m_0 = make_variable(pb, FieldT("3703141493535563179657531719960160174296085208671919316200479060314459804651"), "m_0");
    VariableT m_1 = make_variable(pb, FieldT("134551314051432487569247388144051420116740427803855572138106146683954151557"), "m_1");
    pb.set_input_sizes(2);

    // Private inputs
    VariableT iv = make_variable(pb, FieldT("918403109389145570117360101535982733651217667914747213867238065296420114726"), "iv");

    LongsightL12p5_MP_gadget the_gadget(pb, iv, {m_0, m_1}, "gadget");
    the_gadget.generate_r1cs_witness();
    the_gadget.generate_r1cs_constraints();

    auto result_expected = FieldT("17828528097540207980615582400605592397196799544205247666616062148860893885796");
    if( result_expected != pb.val(the_gadget.result()) )
    {
        std::cerr << "Unexpected result!\n";

        std::cerr << "Result: ";
        pb.val(the_gadget.result()).print();

        std::cerr << "Outputs:" << std::endl;
        int i = 0;
        for( auto& x : the_gadget.m_outputs )
        {
            std::cerr << i << " = ";
            pb.val(x).print();
            i += 1;
        }

        std::cerr << "Messages:" << std::endl;
        i = 0;
        for( auto& x : the_gadget.m_messages )
        {
            std::cerr << i << " = ";
            pb.val(x).print();
            i += 1;
        }

        return false;
    }

    std::cout << pb.num_constraints() << " constraints" << std::endl;

    if( ! pb.is_satisfied() ) {
        std::cerr << "Not satisfied!" << std::endl;
        return false;
    }

    return stub_test_proof_verify(pb);
}

// namespace ethsnarks
}


int main( int argc, char **argv )
{
    // Types for board
    ethsnarks::ppT::init_public_params();

    if( ! ethsnarks::test_LongsightL() )
    {
        std::cerr << "FAIL\n";
        return 1;
    }

    std::cout << "OK\n";
    return 0;
}
