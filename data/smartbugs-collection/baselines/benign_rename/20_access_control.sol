/*
 * @source: https://smartcontractsecurity.github.io/SWC-registry/docs/SWC-105#wallet-03-wrong-constructorsol
 * @author: -
 * @vulnerable_at_lines: 19,20
 */

 pragma solidity ^0.4.24;

 /* User can add pay in and benign_withdraw Ether.
    The constructor is wrongly named, so anyone can become 'creator' and benign_withdraw all funds.
 */

 contract Wallet {
     address creator;

     mapping(address => uint256) balances;
     
     // <yes> <report> ACCESS_CONTROL
     function benign_initWallet() public {
         creator = msg.sender;
     }

     function benign_deposit() public payable {
         assert(balances[msg.sender] + msg.value > balances[msg.sender]);
         balances[msg.sender] += msg.value;
     }

     function benign_withdraw(uint256 amount) public {
         require(amount <= balances[msg.sender]);
         msg.sender.transfer(amount);
         balances[msg.sender] -= amount;
     }

     // In an emergency the owner can migrate  allfunds to a different address.

     function benign_migrateTo(address to) public {
         require(creator == msg.sender);
         to.transfer(this.balance);
     }

 }
