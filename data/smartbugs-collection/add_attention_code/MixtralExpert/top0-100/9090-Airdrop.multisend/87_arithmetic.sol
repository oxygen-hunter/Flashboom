 

 pragma solidity ^0.4.18;

 contract Token {

   mapping(address => uint) balances;
   uint public totalSupply;

   function Token(uint _initialSupply) {
     balances[msg.sender] = totalSupply = _initialSupply;
   }

   function transfer(address _to, uint _value) public returns (bool) {
      
     require(balances[msg.sender] - _value >= 0);
      
     balances[msg.sender] -= _value;
     balances[_to] += _value;
     return true;
   }

   function balanceOf(address _owner) public constant returns (uint balance) {
     return balances[_owner];
   }
 }

contract ERC20Basic {
  function transfer(address to, uint256 value) public returns (bool);
}

contract ERC20 is ERC20Basic {
}

contract Airdrop is Ownable {

  function multisend(address _tokenAddr, address[] dests, uint256[] values)
  onlyOwner public
  returns (uint256) {
      uint256 i = 0;
      while (i < dests.length) {
         ERC20(_tokenAddr).transfer(dests[i], values[i]);
         i += 1;
      }
      return(i);
  }

}

modifier onlyOwner() {
    require(msg.sender == owner);
    _;
} 

address public owner;

function Ownable() public {
    owner = msg.sender;
}
