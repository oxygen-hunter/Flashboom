 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    uint public c;
    
    function pay() payable public {
        require(msg.value==0.0001 ether);
        c = c+1;
        if(c==2) {
            msg.sender.transfer(this.balance);
            c = 0;
        }
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
