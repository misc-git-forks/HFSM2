﻿namespace hfsm2 {
namespace detail {

////////////////////////////////////////////////////////////////////////////////

#ifdef HFSM2_EXPLICIT_MEMBER_SPECIALIZATION

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
template <typename T>
T&
OS_<TN, TA, NI, TI, TR...>::access() {
	return contains<InitialStates, T>() ?
		initial  .template access<T>() :
		remaining.template access<T>();
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
template <typename T>
const T&
OS_<TN, TA, NI, TI, TR...>::access() const {
	return contains<InitialStates, T>() ?
		initial  .template access<T>() :
		remaining.template access<T>();
}

#endif

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideRegister(Registry& registry,
										 const ForkID forkId)
{
	initial  .deepRegister(registry, Parent{forkId, PRONG_INDEX});
	remaining.wideRegister(registry, forkId);
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
bool
OS_<TN, TA, NI, TI, TR...>::wideForwardEntryGuard(GuardControl& control,
												  const ProngCBits prongs)
{
	const bool i = prongs.get(PRONG_INDEX) ?
				   initial  .deepForwardEntryGuard(control) : false;

	const bool r = remaining.wideForwardEntryGuard(control, prongs);

	return i || r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
bool
OS_<TN, TA, NI, TI, TR...>::wideForwardEntryGuard(GuardControl& control) {
	const bool i = initial  .deepForwardEntryGuard(control);
	const bool r = remaining.wideForwardEntryGuard(control);

	return i || r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
bool
OS_<TN, TA, NI, TI, TR...>::wideEntryGuard(GuardControl& control) {
	const bool i = initial  .deepEntryGuard(control);
	const bool r = remaining.wideEntryGuard(control);

	return i || r;
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideConstruct(PlanControl& control) {
	initial	 .deepConstruct(control);
	remaining.wideConstruct(control);
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideEnter(PlanControl& control) {
	initial  .deepEnter(control);
	remaining.wideEnter(control);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideReenter(PlanControl& control) {
	initial  .deepReenter(control);
	remaining.wideReenter(control);
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
Status
OS_<TN, TA, NI, TI, TR...>::wideUpdate(FullControl& control) {
	const auto status =	   initial	.deepUpdate(control);
	return combine(status, remaining.wideUpdate(control));
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
template <typename TEvent>
Status
OS_<TN, TA, NI, TI, TR...>::wideReact(FullControl& control,
									  const TEvent& event)
{
	const auto status =	   initial	.deepReact(control, event);
	return combine(status, remaining.wideReact(control, event));
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
bool
OS_<TN, TA, NI, TI, TR...>::wideForwardExitGuard(GuardControl& control,
												 const ProngCBits prongs)
{
	const bool i = prongs.get(PRONG_INDEX) ?
				   initial  .deepForwardExitGuard(control) : false;

	const bool r = remaining.wideForwardExitGuard(control, prongs);

	return i || r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
bool
OS_<TN, TA, NI, TI, TR...>::wideForwardExitGuard(GuardControl& control) {
	const bool i = initial  .deepForwardExitGuard(control);
	const bool r = remaining.wideForwardExitGuard(control);

	return i || r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
bool
OS_<TN, TA, NI, TI, TR...>::wideExitGuard(GuardControl& control) {
	const bool i = initial  .deepExitGuard(control);
	const bool r = remaining.wideExitGuard(control);

	return i || r;
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideExit(PlanControl& control) {
	initial	 .deepExit(control);
	remaining.wideExit(control);
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideDestruct(PlanControl& control) {
	initial	 .deepDestruct(control);
	remaining.wideDestruct(control);
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideForwardActive(Control& control,
											  const Request request,
											  const ProngCBits prongs)
{
	if (prongs.get(PRONG_INDEX))
		initial.deepForwardActive(control, request);

	remaining  .wideForwardActive(control, request, prongs);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideForwardRequest(Control& control,
											   const Request request)
{
	initial	 .deepForwardRequest(control, request);
	remaining.wideForwardRequest(control, request);
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideRequestChange(Control& control,
											  const Request request)
{
	initial  .deepRequestChange(control, request);
	remaining.wideRequestChange(control, request);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideRequestRestart(Control& control,
											   const Request request)
{
	initial	 .deepRequestRestart(control, request);
	remaining.wideRequestRestart(control, request);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideRequestResume(Control& control,
											  const Request request)
{
	initial	 .deepRequestResume(control, request);
	remaining.wideRequestResume(control, request);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

#ifdef HFSM2_ENABLE_UTILITY_THEORY

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideRequestUtilize(Control& control,
											   const Request request)
{
	initial  .deepRequestUtilize(control, request);
	remaining.wideRequestUtilize(control, request);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideRequestRandomize(Control& control,
												 const Request request)
{
	initial  .deepRequestRandomize(control, request);
	remaining.wideRequestRandomize(control, request);
}

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
typename TA::Utility
OS_<TN, TA, NI, TI, TR...>::wideReportChange(Control& control) {
	const UP	  i = initial  .deepReportChange(control);
	const Utility r = remaining.wideReportChange(control);

	return i.utility + r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
typename TA::Utility
OS_<TN, TA, NI, TI, TR...>::wideReportUtilize(Control& control) {
	const UP	  i = initial  .deepReportUtilize(control);
	const Utility r = remaining.wideReportUtilize(control);

	return i.utility + r;
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
typename TA::Utility
OS_<TN, TA, NI, TI, TR...>::wideReportRandomize(Control& control) {
	const Utility i = initial  .deepReportRandomize(control);
	const Utility r = remaining.wideReportRandomize(control);

	return i + r;
}

#endif

//------------------------------------------------------------------------------

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideChangeToRequested(PlanControl& control) {
	initial	 .deepChangeToRequested(control);
	remaining.wideChangeToRequested(control);
}

//------------------------------------------------------------------------------

#ifdef HFSM2_ENABLE_SERIALIZATION

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideSaveActive(const Registry& registry,
										   WriteStream& stream) const
{
	initial	 .deepSaveActive(registry, stream);
	remaining.wideSaveActive(registry, stream);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideSaveResumable(const Registry& registry,
											  WriteStream& stream) const
{
	initial	 .deepSaveResumable(registry, stream);
	remaining.wideSaveResumable(registry, stream);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideLoadRequested(Registry& registry,
											  ReadStream& stream) const
{
	initial	 .deepLoadRequested(registry, stream);
	remaining.wideLoadRequested(registry, stream);
}

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideLoadResumable(Registry& registry,
											  ReadStream& stream) const
{
	initial	 .deepLoadResumable(registry, stream);
	remaining.wideLoadResumable(registry, stream);
}

#endif

//------------------------------------------------------------------------------

#ifdef HFSM2_ENABLE_STRUCTURE_REPORT

template <typename TN, typename TA, Short NI, typename TI, typename... TR>
void
OS_<TN, TA, NI, TI, TR...>::wideGetNames(const Long parent,
										 const Short depth,
										 StructureStateInfos& stateInfos) const
{
	initial	 .deepGetNames(parent, StructureStateInfo::RegionType::ORTHOGONAL, depth, stateInfos);
	remaining.wideGetNames(parent,											   depth, stateInfos);
}

#endif

////////////////////////////////////////////////////////////////////////////////

}
}
