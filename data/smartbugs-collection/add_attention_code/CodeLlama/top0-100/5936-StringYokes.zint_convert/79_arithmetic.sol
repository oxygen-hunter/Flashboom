 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


    function zint_convert(string key) public pure returns (bytes32 ret) {
        if (bytes(key).length > 32) revert();
        assembly {
          ret := mload(add(key, 32))
        }
    }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
