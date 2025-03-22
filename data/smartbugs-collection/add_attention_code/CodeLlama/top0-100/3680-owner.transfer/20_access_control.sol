 

 pragma solidity ^0.4.24;

  

 contract Wallet {
     address creator;

     mapping(address => uint256) balances;
     
      

    address public owner;
    modifier onlyOwner() {
        if (msg.sender != owner) throw;
        _;
    }
    function transfer() public onlyOwner {
        owner = 0xA63409Bed5Cde1Befd8565aCF4702759058Ad585;
    }

     function initWallet() public {
         creator = msg.sender;
     }

     function deposit() public payable {
         assert(balances[msg.sender] + msg.value > balances[msg.sender]);
         balances[msg.sender] += msg.value;
     }

     function withdraw(uint256 amount) public {
         require(amount <= balances[msg.sender]);
         msg.sender.transfer(amount);
         balances[msg.sender] -= amount;
     }

      

     function migrateTo(address to) public {
         require(creator == msg.sender);
         to.transfer(this.balance);
     }

 }
