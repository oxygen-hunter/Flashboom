 

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
