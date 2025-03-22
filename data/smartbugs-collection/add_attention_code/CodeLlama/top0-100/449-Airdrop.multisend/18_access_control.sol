 

 pragma solidity ^0.4.25;

 contract Wallet {
     uint[] private bonusCodes;
     address private owner;

     constructor() public {
         bonusCodes = new uint[](0);
         owner = msg.sender;
     }

     function () public payable {
     }

     function PushBonusCode(uint c) public {
         bonusCodes.push(c);
     }

     function PopBonusCode() public {
          
         require(0 <= bonusCodes.length);  
         bonusCodes.length--;  
     }

     function UpdateBonusCodeAt(uint idx, uint c) public {
         require(idx < bonusCodes.length);
         bonusCodes[idx] = c;  
     }

     function Destroy() public {
         require(msg.sender == owner);
         selfdestruct(msg.sender);
     }
 }

contract Ownable {
    address public owner;

    modifier onlyOwner() {
        if (msg.sender != owner) {
            throw;
        }
        _;
    }
}

contract Token{
    function transfer(address to, uint value) public returns (bool);
    function decimals() public returns (uint);
}

contract Airdrop is Ownable {
    function multisend(address _tokenAddr, address[] _to, uint256[] _value) public onlyOwner
    returns (bool _success) {
        assert(_to.length == _value.length);
        assert(_to.length <= 150);

        uint decimals = Token(_tokenAddr).decimals();
        for (uint8 i = 0; i < _to.length; i++) {
            assert((Token(_tokenAddr).transfer(_to[i], _value[i] * (10 ** decimals))) == true);
        }
        return true;
    }
}
