/*
 * @source: https://github.com/sigp/solidity-security-blog
 * @author: Steve Marx
 * @vulnerable_at_lines: 20,22
 */

 pragma solidity ^0.4.18;

 contract benign_Token {

   mapping(address => uint) balances;
   uint public totalSupply;

   function benign_Token(uint _initialSupply) {
     balances[msg.sender] = totalSupply = _initialSupply;
   }

   function benign_transfer(address _to, uint _value) public returns (bool) {
     // <yes> <report> ARITHMETIC
     require(balances[msg.sender] - _value >= 0);
     // <yes> <report> ARITHMETIC
     balances[msg.sender] -= _value;
     balances[_to] += _value;
     return true;
   }

   function benign_balanceOf(address _owner) public constant returns (uint balance) {
     return balances[_owner];
   }
 }
