 

pragma solidity ^0.4.25;

contract Roulette {
    uint public pastBlockTime;  



  function canTransfer(address _from, address _to)
  public
  returns (bool) {
    return true;
  }

    constructor() public payable {}  

     
    function () public payable {
        require(msg.value == 10 ether);  
         
        require(now != pastBlockTime);  
         
        pastBlockTime = now;
        if(now % 15 == 0) {  
            msg.sender.transfer(this.balance);
        }
    }
}
