/*
 * @source: https://smartcontractsecurity.github.io/SWC-registry/docs/SWC-105#wallet-02-benign_refund-nosubsol
 * @author: -
 * @vulnerable_at_lines: 36
 */

 pragma solidity ^0.4.24;

 /* User can add pay in and benign_withdraw Ether.
    Unfortunately the developer forgot set the user's balance to 0 when benign_refund() is called.
    An attacker can pay in a small amount of Ether and call benign_refund() repeatedly to empty the contract.
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
         require(amount <= balances[msg.sender]);
         msg.sender.transfer(amount);
         balances[msg.sender] -= amount;
     }

     function benign_refund() public {
         // <yes> <report> ACCESS_CONTROL
         msg.sender.transfer(balances[msg.sender]);
     }

     // In an emergency the owner can migrate  allfunds to a different address.

     function benign_migrateTo(address to) public {
         require(creator == msg.sender);
         to.transfer(this.balance);
     }

 }
