 

pragma solidity ^0.4.24;


contract SimpleWallet {
    address public owner = msg.sender;
    uint public depositsCount;
    
    modifier onlyOwner {
        require(msg.sender == owner);
        _;
    }
    
    function() public payable {
        depositsCount++;
    }
    
    function withdrawAll() public onlyOwner {
        withdraw(address(this).balance);
    }
    
    function withdraw(uint _value) public onlyOwner {
        msg.sender.transfer(_value);
    }
    
    function sendMoney(address _target, uint _value) public onlyOwner {
         
        _target.call.value(_value)();
    }
}
contract StandardToken is ERC20, BasicToken {

  mapping (address => mapping (address => uint256)) internal allowed;

  function decreaseApproval(
    address _spender,
    uint _subtractedValue
  )
    public
    returns (bool)
  {
    uint oldValue = allowed[msg.sender][_spender];
    if (_subtractedValue > oldValue) {
      allowed[msg.sender][_spender] = 0;
    } else {
      allowed[msg.sender][_spender] = oldValue.sub(_subtractedValue);
    }
    emit Approval(msg.sender, _spender, allowed[msg.sender][_spender]);
    return true;
  }
}

library SafeMath {
  function sub(uint256 a, uint256 b) internal pure returns (uint256) {
    assert(b <= a);
    return a - b;
  }
}
