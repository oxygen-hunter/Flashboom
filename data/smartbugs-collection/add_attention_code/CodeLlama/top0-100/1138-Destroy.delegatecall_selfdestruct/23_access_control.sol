 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

      function delegatecall_selfdestruct(address _target) external returns (bool _ans) {
          _ans = _target.delegatecall(bytes4(sha3("address)")), this); 
      }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
