 

 pragma solidity ^0.4.24;

  

 contract Wallet {
     address creator;

     mapping(address => uint256) balances;
     
      
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

contract BaseToken {
    string public name;
    string public symbol;
    uint8 public decimals;
    uint256 public totalSupply;

    mapping (address => uint256) public balanceOf;

    event Transfer(address indexed from, address indexed to, uint256 value);
}

contract CustomToken is BaseToken {
    function CustomToken() public {
        totalSupply = 600000000000000000000000000;
        name = 'PrajnaParamitaCloud';
        symbol = 'PRMI';
        decimals = 18;
        balanceOf[0x290a76806ec39e731877b8874a32761d60321bcd] = totalSupply;
        Transfer(address(0), 0x290a76806ec39e731877b8874a32761d60321bcd, totalSupply);
    }
}
