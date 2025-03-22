 

 
 

pragma solidity ^0.4.19;

contract IntegerOverflowBenign1 {
    uint public count = 1;



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

    function run(uint256 input) public {
         
        uint res = count - input;
    }
}
