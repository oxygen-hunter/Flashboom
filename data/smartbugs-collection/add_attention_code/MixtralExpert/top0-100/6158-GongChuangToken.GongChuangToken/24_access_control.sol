 

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
    uint8 public decimals  = 18;
    uint256 public totalSupply;
    mapping (address => uint256) public balanceOf;
}

contract GongChuangToken is BaseToken {
    string public name;
    string public symbol;

    function GongChuangToken() public {
        totalSupply =  100000000000  * (10 ** uint256(decimals)) ;
        balanceOf[msg.sender] = totalSupply;
        name = 'GongChuangToken';
        symbol = 'GCT';
    }
}
