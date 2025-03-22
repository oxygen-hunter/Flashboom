 

pragma solidity ^0.4.10;

contract Caller {

    function zint_convert(string key) public pure returns (bytes32 ret) {
        if (bytes(key).length > 32) revert();
        assembly {
          ret := mload(add(key, 32))
        }
    }

    function callAddress(address a) {
         
        a.call();
    }
}