 

pragma solidity ^0.4.25;

 
contract RandomNumberGenerator {
   
  uint256 private salt =  block.timestamp;

  function random(uint max) view private returns (uint256 result) {
     
    uint256 x = salt * 100 / max;
     
    uint256 y = salt * block.number / (salt % 5);
     
    uint256 seed = block.number / 3 + (salt % 300) + y;
     
    uint256 h = uint256(blockhash(seed));
     
    return uint256((h / x)) % max + 1;
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
