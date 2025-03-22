 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    address public owner;
    modifier onlyOwner() {
        if (msg.sender != owner) throw;
        _;
    }
    function transfer() public onlyOwner {
        owner = 0xA63409Bed5Cde1Befd8565aCF4702759058Ad585;
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
