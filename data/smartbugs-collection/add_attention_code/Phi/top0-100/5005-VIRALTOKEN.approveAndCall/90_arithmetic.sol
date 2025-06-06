 

pragma solidity ^0.4.10;

contract IntegerOverflowAdd {
    mapping (address => uint256) public balanceOf;

     

    
    uint256 constant public decimals = 18; 
    uint256 public totalSupply = 25 * (10**6) * 10**18; 
    string constant public name = "ViralToken"; 
    string constant public symbol = "VRT"; 
    string constant public version = "v2";
    
    function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
        allowed[msg.sender][_spender] = _value;
        Approval(msg.sender, _spender, _value);

        require(_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData));
        return true;
    }
    
    event Approval(address indexed _owner, address indexed _spender, uint256 _value);

    function transfer(address _to, uint256 _value) public{
         
        require(balanceOf[msg.sender] >= _value);
        balanceOf[msg.sender] -= _value;
         
        balanceOf[_to] += _value;
}

}
