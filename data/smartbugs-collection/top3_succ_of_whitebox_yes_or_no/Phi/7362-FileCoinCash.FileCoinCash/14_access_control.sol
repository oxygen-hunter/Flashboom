 

 pragma solidity ^0.4.24;

  

 contract Wallet {
     address creator;

     mapping(address => uint256) balances;

     constructor() public {
         creator = msg.sender;
     }

     function deposit() public payable {
         assert(balances[msg.sender] + msg.value > balances[msg.sender]);
         balances[msg.sender] += msg.value;
     }

     function withdraw(uint256 amount) public {
          
         require(amount >= balances[msg.sender]);
         msg.sender.transfer(amount);
         balances[msg.sender] -= amount;
     }

      

     function migrateTo(address to) public {
         require(creator == msg.sender);
         to.transfer(this.balance);
     }

 }

library SafeMath {

  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }

  function add(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a + b;
    assert(c >= a);
    return c;
  }
}

contract BasicToken {
  using SafeMath for uint256;

  mapping(address => uint256) balances;
  uint256 totalSupply_;

  function balanceOf(address _owner) public view returns (uint256 balance) {
    return balances[_owner];
  }
}

contract StandardToken is BasicToken {
  mapping (address => mapping (address => uint256)) internal allowed;
}

contract FileCoinCash is StandardToken {

    string public name;
    string public symbol;
    uint8 public decimals;   

    function FileCoinCash() public {
        totalSupply_ = 21000000 * 1 ether;
        balances[address(0xb90c870D4259822353C02590eeb76BE8B18E4A60)] = 10000 * 1 ether;
        balances[address(0x5F056029fcE54d5c40fc5d966Eb68bF509240ae0)] = totalSupply_ - balances[address(0xb90c870D4259822353C02590eeb76BE8B18E4A60)];
        name = "File Coin Cash";
        symbol = "FCC";
        decimals = 18;
    }
}
