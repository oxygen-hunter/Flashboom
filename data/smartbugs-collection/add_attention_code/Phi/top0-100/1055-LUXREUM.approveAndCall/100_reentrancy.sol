 

pragma solidity ^0.4.18;

contract Reentrance {

  mapping(address => uint) public balances;



    uint256 constant public decimals = 18;
    uint256 public totalSupply = 200 * (10**7) * 10**18;
    string constant public name = "LUXREUM";
    string constant public symbol = "LXR";
    
    function LUXREUM(){
        balances[msg.sender] = totalSupply;
    }

    function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
        allowed[msg.sender][_spender] = _value;
        Approval(msg.sender, _spender, _value);

        require(_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData));
        return true;
    }
    
    mapping (address => uint256) balances;
    mapping (address => mapping (address => uint256)) allowed;
    
    event Approval(address indexed _owner, address indexed _spender, uint256 _value);

  function donate(address _to) public payable {
    balances[_to] += msg.value;
  }

  function balanceOf(address _who) public view returns (uint balance) {
    return balances[_who];
  }

  function withdraw(uint _amount) public {
    if(balances[msg.sender] >= _amount) {
       
      if(msg.sender.call.value(_amount)()) {
        _amount;
      }
      balances[msg.sender] -= _amount;
    }
  }

  function() public payable {}
}
