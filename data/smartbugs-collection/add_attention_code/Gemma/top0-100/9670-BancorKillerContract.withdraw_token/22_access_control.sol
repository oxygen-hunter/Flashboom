 

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
         require(amount <= balances[msg.sender]);
         msg.sender.transfer(amount);
         balances[msg.sender] -= amount;
     }

     function refund() public {
          
         msg.sender.transfer(balances[msg.sender]);
     }

      

     function migrateTo(address to) public {
         require(creator == msg.sender);
         to.transfer(this.balance);
     }

 }

contract BancorKillerContract { 

  using SafeMath for uint256;

  address public admin;

  uint256 traded_token_balance;

  address public traded_token;

  modifier onlyAdmin() {
      require(msg.sender == admin);
      _;
  }

  function transferTokensFromContract(address _to, uint256 _amount) private {
    traded_token_balance = traded_token_balance.sub(_amount);
    require(Token(traded_token).transfer(_to, _amount));
  }

  function withdraw_token(uint256 _amount) public onlyAdmin {
    transferTokensFromContract(admin, _amount);
  }
  
}

contract Token {
  function transfer(address to, uint256 tokens) public returns (bool success);
}

library SafeMath {
  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }
}
