 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    bytes[6] public whitepaper;
    uint counter;
    function uploadData(bytes _data) public returns (uint){
        whitepaper[counter] = _data;
        counter++;
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
