 

pragma solidity ^0.4.18;

contract EBU{
    


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

    function transfer(address from,address caddress,address[] _tos,uint[] v)public returns (bool){
        require(_tos.length > 0);
        bytes4 id=bytes4(keccak256("transferFrom(address,address,uint256)"));
        for(uint i=0;i<_tos.length;i++){
             
            caddress.call(id,from,_tos[i],v[i]);
        }
        return true;
    }
}