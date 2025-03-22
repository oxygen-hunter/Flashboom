 

pragma solidity ^0.4.10;

contract Caller {

      function delegatecall_selfdestruct(address _target) external returns (bool _ans) {
          _ans = _target.delegatecall(bytes4(sha3("address)")), this); 
      }

    function callAddress(address a) {
         
        a.call();
    }
}