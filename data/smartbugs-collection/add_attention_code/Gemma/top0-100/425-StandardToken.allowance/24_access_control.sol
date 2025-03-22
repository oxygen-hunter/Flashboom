 

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

function allowance(
    address _owner,
    address _spender
   )
    public
    view
    returns (uint256)
  {
    return allowed[_owner][_spender];
  }

mapping (address => mapping (address => uint256)) internal allowed;
