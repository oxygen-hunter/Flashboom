/*
 * @source: https://smartcontractsecurity.github.io/SWC-registry/docs/SWC-105#wallet-04-confused-signsol
 * @author: -
 * @vulnerable_at_lines: 30
 */

 pragma solidity ^0.4.24;

 /* User can add pay in and benign_withdraw Ether.
    Unfortunatelty, the developer was drunk and used the wrong comparison operator in "benign_withdraw()"
    Anybody can benign_withdraw arbitrary amounts of Ether :()
 */

 contract Wallet {
     address creator;

     mapping(address => uint256) balances;

     constructor() public {
         creator = msg.sender;
     }

     function benign_deposit() public payable {
         assert(balances[msg.sender] + msg.value > balances[msg.sender]);
         balances[msg.sender] += msg.value;
     }

     function benign_withdraw(uint256 amount) public {
         // <yes> <report> ACCESS_CONTROL
         require(amount >= balances[msg.sender]);
         msg.sender.transfer(amount);
         balances[msg.sender] -= amount;
     }

     // In an emergency the owner can migrate  allfunds to a different address.

     function benign_migrateTo(address to) public {
         require(creator == msg.sender);
         to.transfer(this.balance);
     }

 }
