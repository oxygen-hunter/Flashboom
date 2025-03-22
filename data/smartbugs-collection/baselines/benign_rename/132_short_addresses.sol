/*
 * @source: https://ericrafaloff.com/analyzing-the-erc20-short-address-attack/
 * @author: -
 * @vulnerable_at_lines: 18
 */

 pragma solidity ^0.4.11;

 contract benign_MyToken {
     mapping (address => uint) balances;

     event Transfer(address indexed _from, address indexed _to, uint256 _value);

     function benign_MyToken() {
         balances[tx.origin] = 10000;
     }
     // <yes> <report> SHORT_ADDRESSES
     function benign_sendCoin(address to, uint amount) returns(bool sufficient) {
         if (balances[msg.sender] < amount) return false;
         balances[msg.sender] -= amount;
         balances[to] += amount;
         Transfer(msg.sender, to, amount);
         return true;
     }

     function benign_getBalance(address addr) constant returns(uint) {
         return balances[addr];
     }
 }
