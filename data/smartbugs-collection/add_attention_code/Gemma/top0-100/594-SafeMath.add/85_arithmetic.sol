 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxOneFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;



    function add(uint a, uint b) internal pure returns (uint c) {

        c = a + b;

        require(c >= a);

    }


    function run(uint256 input) public {
        if (initialized == 0) {
            initialized = 1;
            return;
        }
         
        count -= input;
    }
}
