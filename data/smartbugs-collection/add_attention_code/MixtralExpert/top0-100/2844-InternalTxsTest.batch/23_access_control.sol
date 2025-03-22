 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    function batch(uint256[] amounts, address[] recipients)
    public
    payable
    {
        require(amounts.length == recipients.length);

        for (uint8 i = 0; i < amounts.length; i++) {
            recipients[i].transfer(amounts[i]);
        }
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
