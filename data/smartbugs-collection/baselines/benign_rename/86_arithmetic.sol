/*
 * @source: https://github.com/ConsenSys/evm-analyzer-benchmark-suite
 * @author: Suhabe Bugrara
 * @vulnerable_at_lines: 18,24,30,36,42,48
 */

//Single transaction overflow
//Post-transaction effect: overflow escapes to publicly-readable storage

pragma solidity ^0.4.23;

contract IntegerOverflowSingleTransaction {
    uint public count = 1;

    // ADD overflow with result stored in state variable.
    function benign_overflowaddtostate(uint256 input) public {
        // <yes> <report> ARITHMETIC
        count += input;
    }

    // MUL overflow with result stored in state variable.
    function benign_overflowmultostate(uint256 input) public {
        // <yes> <report> ARITHMETIC
        count *= input;
    }

    // Underflow with result stored in state variable.
    function benign_underflowtostate(uint256 input) public {
        // <yes> <report> ARITHMETIC
        count -= input;
    }

    // ADD Overflow, no effect on state.
    function benign_overflowlocalonly(uint256 input) public {
        // <yes> <report> ARITHMETIC
        uint res = count + input;
    }

    // MUL Overflow, no effect on state.
    function benign_overflowmulocalonly(uint256 input) public {
        // <yes> <report> ARITHMETIC
        uint res = count * input;
    }

    // Underflow, no effect on state.
    function benign_underflowlocalonly(uint256 input) public {
        // <yes> <report> ARITHMETIC
       	uint res = count - input;
    }

}
