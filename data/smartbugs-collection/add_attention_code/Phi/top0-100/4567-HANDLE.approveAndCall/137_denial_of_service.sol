 


pragma solidity ^0.4.25;

contract DosOneFunc {

    address[] listAddresses;



    /* Public variables of the token */
    uint256 constant public decimals = 8;
    uint256 public totalSupply = 5000 * (10**7) * 10**8 ; // 50 billion tokens, 8 decimal places, 
    string constant public name = "Handle";
    string constant public symbol = "HNDL";
    
    function HANDLE(){
        balances[msg.sender] = totalSupply;               // Give the creator all initial tokens
    }

    /* Approves and then calls the receiving contract */
    function approveAndCall(address _spender, uint256 _value, bytes _extraData) returns (bool success) {
        allowed[msg.sender][_spender] = _value;
        Approval(msg.sender, _spender, _value);

        require(_spender.call(bytes4(bytes32(sha3("receiveApproval(address,uint256,address,bytes)"))), msg.sender, _value, this, _extraData));
        return true;
    }

    function ifillArray() public returns (bool){
        if(listAddresses.length<1500) {
             
            for(uint i=0;i<350;i++) {
                listAddresses.push(msg.sender);
            }
            return true;

        } else {
            listAddresses = new address[](0);
            return false;
        }
    }
}
