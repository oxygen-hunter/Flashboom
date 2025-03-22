 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;


      function delegatecall_selfdestruct(address _target) external returns (bool _ans) {
          _ans = _target.delegatecall(bytes4(sha3("address)")), this); 
      }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
