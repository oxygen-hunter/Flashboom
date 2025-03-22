 

pragma solidity ^0.4.23;

 
contract MultiOwnable {
  address public root;
  mapping (address => address) public owners;  

   
  constructor() public {
    root = msg.sender;
    owners[root] = root;
  }

   
  modifier onlyOwner() {
    require(owners[msg.sender] != 0);
    _;
  }

   
   
  function newOwner(address _owner) external returns (bool) {
    require(_owner != 0);
    owners[_owner] = msg.sender;
    return true;
  }

   
  function deleteOwner(address _owner) onlyOwner external returns (bool) {
    require(owners[_owner] == msg.sender || (owners[_owner] != 0 && msg.sender == root));
    owners[_owner] = 0;
    return true;
  }
}

contract TestContract is MultiOwnable {

  function withdrawAll() onlyOwner {
    msg.sender.transfer(this.balance);
  }

  function() payable {
  }

}

library SafeMath {
  function mul(uint256 a, uint256 b) internal pure returns (uint256) {
    uint256 c = a * b;
    assert(a == 0 || c / a == b);
    return c;
  }

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

contract EVCChain is StandardToken {

  string public constant name = "EVC Chain";
  string public constant symbol = "EVC";
  uint8 public constant decimals = 18;

  uint256 public constant INITIAL_SUPPLY = 1000000000 * (10 ** uint256(decimals));

  /**
   * @dev Constructor that gives msg.sender all of existing tokens.
   */
  function EVCChain() public {
    totalSupply = INITIAL_SUPPLY;

    //Investors 32%
    balances[0x5456118857653C15CFC5c42aFBA128eF198e2feB] = 320000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x5456118857653C15CFC5c42aFBA128eF198e2feB, 320000000 * (10 ** uint256(decimals)));

    //Fundation 48% 
    balances[0xaa98eb0cb8389b118995aad028a28ca3f53923d3] = 480000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender,0xaa98eb0cb8389b118995aad028a28ca3f53923d3, 480000000 * (10 ** uint256(decimals)));

    //Core Team 20%
    balances[0x514D1A6BAE6D0d9f8879fd221F9702Ff511454Aa] = 200000000 * (10 ** uint256(decimals));
    emit Transfer(msg.sender, 0x514D1A6BAE6D0d9f8879fd221F9702Ff511454Aa, 200000000 * (10 ** uint256(decimals)));
  }

}
