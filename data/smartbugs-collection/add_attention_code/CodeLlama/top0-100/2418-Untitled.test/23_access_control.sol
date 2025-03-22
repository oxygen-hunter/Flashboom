 

 
pragma solidity ^0.4.0;

contract SimpleSuicide {
   

    
    event Buy(address indexed beneficiary, uint256 payedEther, uint256 tokenAmount);
    
    function test(string nothing) public returns(string hello) {
        emit Buy(msg.sender, now, now + 36000);
        hello = nothing;
    }

  function sudicideAnyone() {
    selfdestruct(msg.sender);
  }

}
