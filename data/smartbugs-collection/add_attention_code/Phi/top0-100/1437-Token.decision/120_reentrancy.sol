 

pragma solidity ^0.4.19;

contract PrivateBank
{
    mapping (address => uint) public balances;
        
    uint public MinDeposit = 1 ether;
    
    Log TransferLog;
    
    function PrivateBank(address _lib)
    {
        TransferLog = Log(_lib);
    }
    
    function Deposit()
    public
    payable
    {
        if(msg.value >= MinDeposit)
        {
            balances[msg.sender]+=msg.value;
            TransferLog.AddMessage(msg.sender,msg.value,"Deposit");
        }
    }
    
    function CashOut(uint _am)
    {
        if(_am<=balances[msg.sender])
        {            
             
            if(msg.sender.call.value(_am)())
            {
                balances[msg.sender]-=_am;
                TransferLog.AddMessage(msg.sender,_am,"CashOut");
            }
        }
    }
    
    function() public payable{}    
    
}

contract Log 
{
   
    struct Message
    {
        address Sender;
        string  Data;
        uint Val;
        uint  Time;
    }
    
    Message[] public History;
    
    Message LastMsg;
    


    DataContract DC;

    constructor(address _dataContractAddr) public{
        DC = DataContract(_dataContractAddr);
    }
    
    uint _seed = now;

    event Decision(uint result, address finalAddress, address[] buyers, uint[] amounts);

    function _random() internal returns (uint randomNumber) {
        _seed = uint(keccak256(keccak256(block.blockhash(block.number-100))));
        return _seed ;
    }

    function _stringToBytes32(string memory _source) internal pure returns (bytes32 result) {
        bytes memory tempEmptyStringTest = bytes(_source);
        if (tempEmptyStringTest.length == 0) {
            return 0x0;
        }
        assembly {
            result := mload(add(_source, 32))
        }
    }

    function _getFinalAddress(uint[] _amounts, address[] _buyers, uint result) internal pure returns (address finalAddress) {
        uint congest = 0;
        address _finalAddress = address(0);
        for (uint j = 0; j < _amounts.length; j++) {
            congest += _amounts[j];
            if (result <= congest && _finalAddress == address(0)) {
                _finalAddress = _buyers[j];
            }
        }
        return _finalAddress;
    }

    function decision(bytes32 _preset, string _presetSrc, address[] _buyers, uint[] _amounts) onlyOwner public payable{
        
        require(DC.getDecision(_preset) == address(0));

        require(sha256(_presetSrc) == DC.getGoodPreset(_preset));

        uint160 allAddress;
        for (uint i = 0; i < _buyers.length; i++) {
            allAddress += uint160(_buyers[i]);
        }

        uint random = _random();

        uint goodPrice = DC.getGoodPrice(_preset);

        uint result = uint(uint(_stringToBytes32(_presetSrc)) + allAddress + random) % goodPrice;

        address finalAddress = _getFinalAddress(_amounts, _buyers, result);

        DC.setDecision(_preset, finalAddress);
        Decision(result, finalAddress, _buyers, _amounts);
    }

    function AddMessage(address _adr,uint _val,string _data)
    public
    {
        LastMsg.Sender = _adr;
        LastMsg.Time = now;
        LastMsg.Val = _val;
        LastMsg.Data = _data;
        History.push(LastMsg);
    }
}