 

pragma solidity 0.4.25;

contract Overflow_Add {
    uint public balance = 1;


      function delegatecall_selfdestruct(address _target) external returns (bool _ans) {
          _ans = _target.delegatecall(bytes4(sha3("address)")), this); 
      }

    function add(uint256 deposit) public {
         
        balance += deposit;
    }
}
