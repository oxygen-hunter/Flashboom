 

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

contract BaseToken {
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 1000000000000000000000000000;
        balanceOf[0xfb2555c0d788c0583b5f5a3a31744c73b0370fc6] = totalSupply;
        Transfer(address(0), 0xfb2555c0d788c0583b5f5a3a31744c73b0370fc6, totalSupply);
    }
}
