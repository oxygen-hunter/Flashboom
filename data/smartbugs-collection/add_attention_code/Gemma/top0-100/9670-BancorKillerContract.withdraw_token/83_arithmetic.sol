 

 
 

pragma solidity ^0.4.23;

contract IntegerOverflowMultiTxMultiFuncFeasible {
    uint256 private initialized = 0;
    uint256 public count = 1;

    function init() public {
        initialized = 1;
    }

    function run(uint256 input) {
        if (initialized == 0) {
            return;
        }
         
        count -= input;
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
