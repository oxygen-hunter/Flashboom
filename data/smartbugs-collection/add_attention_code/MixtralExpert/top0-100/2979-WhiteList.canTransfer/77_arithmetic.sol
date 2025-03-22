 

 

pragma solidity ^0.4.11;

contract IntegerOverflowMappingSym1 {
    mapping(uint256 => uint256) map;



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

    function init(uint256 k, uint256 v) public {
         
        map[k] -= v;
    }
}
