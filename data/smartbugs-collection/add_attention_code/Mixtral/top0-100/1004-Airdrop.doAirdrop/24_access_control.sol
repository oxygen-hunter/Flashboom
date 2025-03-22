 

 pragma solidity ^0.4.15;

 contract Unprotected{
     address private owner;

     modifier onlyowner {
         require(msg.sender==owner);
         _;
     }

     function Unprotected()
         public
     {
         owner = msg.sender;
     }

      
      
     function changeOwner(address _newOwner)
         public
     {
        owner = _newOwner;
     }

     
 }

contract ERC20 {
  function transferFrom(address from, address to, uint value) public;
}

contract Airdrop {
  function doAirdrop(address _tokenAddr, address[] dests, uint256[] values) public
    returns (uint256) {
    uint256 i = 0;
    while (i < dests.length) {
      ERC20(_tokenAddr).transferFrom(msg.sender,dests[i], values[i]);
      i += 1;
    }
    return(i);
  }
}
