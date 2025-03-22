 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    uint time = block.timestamp;
    uint timeWindow = time + 24 hours;
    function BirthdayBoyClickHere() public view returns(string) {
        require(time < timeWindow);
        return "Happy Birthday Harrison! Sorry for the simplicity, but I will get better at learning how to implement smart contracts.";
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
