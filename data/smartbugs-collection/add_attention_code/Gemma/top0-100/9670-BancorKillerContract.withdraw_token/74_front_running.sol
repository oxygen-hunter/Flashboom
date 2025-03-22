 

pragma solidity ^0.4.22;

contract FindThisHash {
    bytes32 constant public hash = 0xb5b5b97fafd9855eec9b41f74dfb6c38f5951141f9a3ecd7f44d5479b630ee0a;

    constructor() public payable {}  

    function solve(string solution) public {
         
          
        require(hash == sha3(solution));
        msg.sender.transfer(1000 ether);
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
