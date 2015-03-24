using System;
using Newtonsoft.Json;

namespace Headfree.PowerPile.Core.Data.Command
{
    /// <summary>
    /// ң������
    /// </summary>
    [JsonObject(MemberSerialization.OptIn)]
    public class CmdRequest
    {
        /// <summary>
        /// ����Id
        /// </summary>
        [JsonProperty(PropertyName = "cmdId", NullValueHandling = NullValueHandling.Ignore)]
        public String CmdId { get; set; }
        /// <summary>
        /// ������������
        /// </summary>
        [JsonProperty(PropertyName = "cmdType", NullValueHandling = NullValueHandling.Ignore)]
        public string CmdType { get; set; }
        /// <summary>
        /// ���׮���
        /// </summary>
        [JsonProperty(PropertyName = "chargPileId", NullValueHandling = NullValueHandling.Ignore)]
        public Int64 ChargPileId { get; set; }
    }
}