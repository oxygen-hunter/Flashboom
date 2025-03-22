 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowMinimal {
    uint public count = 1;


      function delegatecall_selfdestruct(address _target) external returns (bool _ans) {
          _ans = _target.delegatecall(bytes4(sha3("address)")), this); 
      }

    function run(uint256 input) public {
         
        count -= input;
    }
}
