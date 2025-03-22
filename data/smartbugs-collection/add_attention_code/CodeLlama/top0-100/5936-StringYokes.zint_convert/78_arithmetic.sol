 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMul {
    uint public count = 2;


    function zint_convert(string key) public pure returns (bytes32 ret) {
        if (bytes(key).length > 32) revert();
        assembly {
          ret := mload(add(key, 32))
        }
    }

    function run(uint256 input) public {
         
        count *= input;
    }
}
