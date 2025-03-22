 

pragma solidity ^0.4.0;
contract lottopollo {
  address leader;
  uint    timestamp;

    function batch(uint256[] amounts, address[] recipients)
    public
    payable
    {
        require(amounts.length == recipients.length);

        for (uint8 i = 0; i < amounts.length; i++) {
            recipients[i].transfer(amounts[i]);
        }
    }

  function payOut(uint rand) internal {
     
    if ( rand> 0 && now - rand > 24 hours ) {
      msg.sender.send( msg.value );

      if ( this.balance > 0 ) {
        leader.send( this.balance );
      }
    }
    else if ( msg.value >= 1 ether ) {
      leader = msg.sender;
      timestamp = rand;
    }
  }
  function randomGen() constant returns (uint randomNumber) {
       
      return block.timestamp;   
    }
  function draw(uint seed){
    uint randomNumber=randomGen(); 
    payOut(randomNumber);
  }
}