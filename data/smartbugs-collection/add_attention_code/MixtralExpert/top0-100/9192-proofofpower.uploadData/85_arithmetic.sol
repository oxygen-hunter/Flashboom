 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxOneFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;


    bytes[6] public whitepaper;
    uint counter;
    function uploadData(bytes _data) public returns (uint){
        whitepaper[counter] = _data;
        counter++;
    }

    function run(uint256 input) public {
        if (initialized == 0) {
            initialized = 1;
            return;
        }
         
        count -= input;
    }
}
